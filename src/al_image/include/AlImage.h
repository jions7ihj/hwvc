/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWVC_ANDROID_ALIMAGE_H
#define HWVC_ANDROID_ALIMAGE_H

#include "Unit.h"
#include "AlTexAllocator.h"
#include "HwAbsTexture.h"
#include "AlImageLayerManager.h"

class AlImage : public Unit {
public:
    AlImage(string alias);

    virtual ~AlImage();

    bool onCreate(AlMessage *msg) override;

    bool onDestroy(AlMessage *msg) override;

    /// 表示图层有更新，比如新增或删除图层
    /// FORMAT:
    /// +--------------------------------------+
    /// | msg::obj     | msg::arg1 | msg::arg2 |
    /// +--------------------------------------+
    /// | none         | none      | none      |
    /// +--------------------------------------+
    /// \param msg
    /// \return
    bool onUpdateLayer(AlMessage *msg);

    /// 重绘所有图层，并绘制到窗口
    /// FORMAT:
    /// +--------------------------------------+
    /// | msg::obj     | msg::arg1 | msg::arg2 |
    /// +--------------------------------------+
    /// | none         | none      | none      |
    /// +--------------------------------------+
    /// \param msg
    /// \return
    bool onInvalidate(AlMessage *m);

    /// 把所有图层清楚，并导入.qua文件
    /// FORMAT:
    /// +--------------------------------------------------+
    /// | msg::obj     | msg::arg1 | msg::arg2 | msg::desc |
    /// +--------------------------------------------------+
    /// | none         | none      | none      | .qua file |
    /// +--------------------------------------------------+
    /// \param msg
    /// \return
    bool onImport(AlMessage *m);

private:
    void _notifyAll(int32_t flag = 0);

    void _notifyDescriptor(AlImageLayer *layer);

private:
    AlTexAllocator *texAllocator = nullptr;
    /// +------------------+
    /// |     Model        |
    /// +------------------+
    std::vector<AlImageLayerModel *> *getLayers();

    AlImageLayerManager mLayerManager;
};


#endif //HWVC_ANDROID_ALIMAGE_H
