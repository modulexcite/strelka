// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Starka
// Copyright (c) 2009-2014 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/sequencing/licenses/>
//

/// \file

/// \author Morten Kallberg
///

#include "blt_util/ranksum.hh"

#include <iostream>

using namespace std;


static
double
get_z_score(const int n1, const int n2, const double w1)
{
    const double mean = n1*(n1+n2+1)/2.0;
    const double var  = sqrt(n2*mean/6.0);
    if (static_cast<int>(var)==0)
    {
        return 0.0;
    }
    return (w1-mean)/var;
}



// return the U statistic
double
ranksum::get_u_stat() const
{
    //	cout << "doing U stat" << endl;
    double R1 = 0;
    double R2 = 0;
    int N1 = 0;
    int N2 = 0;

    //loop over all observations
    vector<int> myvector = this->getSpace();
    for (const auto& key : myvector)
    {
        // get the observation counts for reference and alt
        const ranksumObs robs = this->get_obs_count(key);
        int obs1 = robs.ref;
        int obs2 = robs.nonRef;
        double rank_weight = (2*(N1+N2+1) + (obs1+obs2)-1)/2.0;
        R1 += rank_weight*obs1;
        R2 += rank_weight*obs2;
        N1 += obs1;
        N2 += obs2;
        //		cout << key << "\t{"<< obs1 << ", " << obs2 << "}" << " sum: " << obs ;
        //		cout << " weight " << rank_weight << " U1: " << U1 << " U2: " << U2 << endl;
    }

    //return the z-score for the smaller of U1 and U2 assuming a gaussian approx.
    if (R1>R2)
    {
        return get_z_score(N2,N1,R2);
    }
    else
    {
        return get_z_score(N1,N2,R1);
    }
}



// output specification
ostream&
operator<< (ostream& out, const ranksum& r)
{
    double z = r.get_u_stat();
    out << "elements in space:\n";
    out << "[";
    const vector<int> myvector = r.getSpace();
    for (const int& val : myvector)
        out << ' ' << val;
    out << "]\n";
    out << "Z-score: " << z << '\n';
    return out;
}

