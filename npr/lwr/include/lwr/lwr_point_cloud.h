#ifndef LWR_POINT_CLOUD_H_
#define LWR_POINT_CLOUD_H_

#include <nanoflann.hpp>
#include <armadillo>

namespace lwr{

using namespace std;
using namespace nanoflann;

struct PointCloud
{

    const arma::mat& pts;

    PointCloud(const arma::mat& pts):pts(pts){

    }

    arma::colvec3 getPoint(size_t index){
        return pts.row(index).st();
    }

    // Must return the number of data points
    inline size_t kdtree_get_point_count() const { return pts.n_rows; }

    // Returns the distance between the vector "p1[0:size-1]" and the data point with index "idx_p2" stored in the class:
    inline double kdtree_distance(const double *p1, const size_t idx_p2,size_t size) const
    {
        return sqrt((p1[0] - pts(idx_p2,0))*(p1[0] - pts(idx_p2,0)) + (p1[1] - pts(idx_p2,1))*(p1[1] - pts(idx_p2,1)) + (p1[2] - pts(idx_p2,2))*(p1[2] - pts(idx_p2,2)));
    }

    inline double kdtree_get_pt(const size_t idx, int dim) const
    {
        return pts(idx,dim);
    }

    template <class BBOX>
    bool kdtree_get_bbox(BBOX &bb) const { return false; }

};

}

#endif
