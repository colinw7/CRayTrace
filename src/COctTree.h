#ifndef COCT_TREE_H
#define COCT_TREE_H

//     ________
//   /_  /_  / |
//  /   /   /| |
// +---+---+ |/|
// | 2 | 3 |/| |
// +---+---+ |/
// | 0 | 1 |/
// +---+---+

#include <vector>

template<typename DATA, typename BBOX, typename T=double>
class COctTree {
 private:
  enum { NUM_TREES = 8 };

  enum {
    LEFT   = 0, RIGHT = (1<<0),
    BOTTOM = 0, TOP   = (1<<1),
    NEAR   = 0, FAR   = (1<<2),

    NBL = (NEAR | BOTTOM | LEFT ), // 0
    NBR = (NEAR | BOTTOM | RIGHT), // 1
    NTL = (NEAR | TOP    | LEFT ), // 2
    NTR = (NEAR | TOP    | RIGHT), // 3
    FBL = (FAR  | BOTTOM | LEFT ), // 4
    FBR = (FAR  | BOTTOM | RIGHT), // 5
    FTL = (FAR  | TOP    | LEFT ), // 6
    FTR = (FAR  | TOP    | RIGHT), // 7
  };

 public:
  typedef std::vector<DATA *> DataList;

 public:
  COctTree(const BBOX &bbox=BBOX()) :
   parent_(NULL), bbox_(bbox), dataList_(), splitSize_(16), split_(false) {
    memset(trees_, 0, sizeof(trees_));
  }

 ~COctTree() {
    for (uint i = 0; i < NUM_TREES; ++i)
      delete trees_[i];
  }

 private:
  COctTree(COctTree *parent, const BBOX &bbox=BBOX()) :
   parent_(parent), bbox_(bbox), dataList_(), splitSize_(16), split_(false) {
    memset(trees_, 0, sizeof(trees_));
  }

 public:
  void setBBox(const BBOX &bbox=BBOX()) {
    assert(dataList_.empty() && ! split_);

    bbox_ = bbox;
  }

  // get parent tree
  COctTree *getParent() const { return parent_; }

  // get if tree has been split
  bool isSplit() const { return split_; }

  // get bounding box
  const BBOX &getBBox() const { return bbox_; }

  // get child tree
  const COctTree *getChild(uint i) const { return trees_[i]; }

  COctTree *getChild(uint i) { return trees_[i]; }

  // get empty
  bool empty() const { return dataList_.empty(); }

  // get num data
  uint getNumData() const { return dataList_.size(); }

  // get unsplit and empty
  bool dead() const { return ! split_ && dataList_.empty(); }

  // get data list
  const DataList &getDataList() const { return dataList_; }

  // get split size
  uint getSplitSize() const { return splitSize_; }

  // set split size
  void setSplitSize(uint size) { splitSize_ = size; }

 public:
  void addData(DATA *d) {
    const BBOX &bbox = d->getBBox();

    addData(bbox, d);
  }

 private:
  void addData(const BBOX &bbox, DATA *d) {
    if (! split_) {
      uint numData = dataList_.size();

      if (numData >= splitSize_) {
        if (split())
          addData(bbox, d);
        else
          dataList_.push_back(d);
      }
      else
        dataList_.push_back(d);
    }
    else {
      int id = getChildId(bbox);

      if (id >= 0)
        trees_[id]->addData(bbox, d);
      else
        dataList_.push_back(d);
    }
  }

 private:
  bool split() {
    assert(! split_);

    split_ = true;

    T xmin = bbox_.getXMin(), ymin = bbox_.getYMin(), zmin = bbox_.getZMin();
    T xmax = bbox_.getXMax(), ymax = bbox_.getYMax(), zmax = bbox_.getZMax();
    T xmid = (xmin + xmax)/2, ymid = (ymin + ymax)/2, zmid = (zmin + zmax)/2;

    trees_[0] = new COctTree(this, BBOX(xmin, ymin, zmin, xmid, ymid, zmid));
    trees_[1] = new COctTree(this, BBOX(xmid, ymin, zmin, xmax, ymid, zmid));
    trees_[2] = new COctTree(this, BBOX(xmin, ymid, zmin, xmid, ymax, zmid));
    trees_[3] = new COctTree(this, BBOX(xmid, ymid, zmin, xmax, ymax, zmid));
    trees_[4] = new COctTree(this, BBOX(xmin, ymin, zmid, xmid, ymid, zmax));
    trees_[5] = new COctTree(this, BBOX(xmid, ymin, zmid, xmax, ymid, zmax));
    trees_[6] = new COctTree(this, BBOX(xmin, ymid, zmid, xmid, ymax, zmax));
    trees_[7] = new COctTree(this, BBOX(xmid, ymid, zmid, xmax, ymax, zmax));

    if (xmin == xmax || ymin == ymax || zmin == zmax)
      return false;

    DataList dataList;

    uint numData = dataList_.size();

    uint pushed = 0;

    for (uint i = 0; i < numData; ++i) {
      const BBOX &bbox1 = dataList_[i]->getBBox();

      T xmin1 = bbox1.getXMin(), ymin1 = bbox1.getYMin(), zmin1 = bbox1.getZMin();
      T xmax1 = bbox1.getXMax(), ymax1 = bbox1.getYMax(), zmax1 = bbox1.getZMax();

      if ((xmax1 > xmid && xmin1 < xmid) ||
          (ymax1 > ymid && ymin1 < ymid) ||
          (zmax1 > zmid && zmin1 < zmid))
        dataList.push_back(dataList_[i]);
      else {
        uint id = (xmax1 <= xmid ? LEFT   : RIGHT) |
                  (ymax1 <= ymid ? BOTTOM : TOP  ) |
                  (zmax1 <= zmid ? NEAR   : FAR  );

        trees_[id]->addData(bbox1, dataList_[i]);

        ++pushed;
      }
    }

    if (! pushed)
      return false;

    dataList_ = dataList;

    return true;
  }

 public:
  // remove data from tree
  void remove(DATA *data) {
    const BBOX &bbox = data->getBBox();

    removeData(data, bbox);
  }

 private:
  void removeData(DATA *data, const BBOX &bbox) {
    if (split_) {
      int id = getChildId(bbox);

      if (id >= 0)
        trees_[id]->removeData(data, bbox);
      else
        dataList_.remove(data);
    }
    else
      dataList_.remove(data);
  }

 public:
  void reset() {
    dataList_.clear();

    if (split_) {
      for (uint i = 0; i < NUM_TREES; ++i) {
        delete trees_[i];

        trees_[i] = NULL;
      }
    }

    split_ = false;
  }

 public:
  uint numData() const {
    uint n = dataList_.size();

    if (split_) {
      for (uint i = 0; i < NUM_TREES; ++i)
        n += trees_[i]->numData();
    }

    return n;
  }

 private:
  int getChildId(const BBOX &bbox) const {
    T xmin = bbox_.getXMin(), ymin = bbox_.getYMin(), zmin = bbox_.getZMin();
    T xmax = bbox_.getXMax(), ymax = bbox_.getYMax(), zmax = bbox_.getZMax();
    T xmid = (xmin + xmax)/2, ymid = (ymin + ymax)/2, zmid = (zmin + zmax)/2;

    T xmin1 = bbox.getXMin(), ymin1 = bbox.getYMin(), zmin1 = bbox.getZMin();
    T xmax1 = bbox.getXMax(), ymax1 = bbox.getYMax(), zmax1 = bbox.getZMax();

    if ((xmax1 > xmid && xmin1 < xmid) ||
        (ymax1 > ymid && ymin1 < ymid) ||
        (zmax1 > zmid && zmin1 < zmid))
      return -1;
    else
      return (xmax1 <= xmid ? LEFT   : RIGHT) |
             (ymax1 <= ymid ? BOTTOM : TOP  ) |
             (zmax1 <= zmid ? NEAR   : FAR  );
  }

 private:
  COctTree *parent_;
  BBOX      bbox_;
  DataList  dataList_;
  ushort    splitSize_;
  bool      split_;
  COctTree *trees_[NUM_TREES];
};

#endif
