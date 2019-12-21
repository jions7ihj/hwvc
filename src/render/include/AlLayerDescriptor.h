/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWVC_ANDROID_ALLAYERDESCRIPTOR_H
#define HWVC_ANDROID_ALLAYERDESCRIPTOR_H

#include "Unit.h"
#include "AlImageLayer.h"
#include "AlLayerMeasure.h"
#include "HwResult.h"
#include "AlSize.h"
#include "AlImgLayerDescription.h"

class AlLayerDescriptor : public Unit {
public:
    AlLayerDescriptor(const string &alias);

    virtual ~AlLayerDescriptor();

    bool onCreate(AlMessage *msg) override;

    bool onDestroy(AlMessage *msg) override;

    bool onMeasure(AlMessage *msg);

    bool onCanvasSizeUpdate(AlMessage *msg);

private:
    /// Measure all params for canvas
    /// \param drawModel
    /// \return {@link HwResult}
    HwResult _measure(AlImageLayer *layer, AlImageLayerDrawModel *description);

    /// Measure all operate`s params for canvas
    /// \param model
    /// \param description
    /// \return {@link HwResult}
    HwResult _measureOperate(std::vector<AlAbsOperateModel *> *opts,
                             AlImgLayerDescription &model,
                             AlImageLayerDrawModel *description);

    void notifyCanvas(AlImageLayerDrawModel *description);

private:
    AlLayerMeasure aMeasure;
    AlSize aCanvasSize;
};


#endif //HWVC_ANDROID_ALLAYERDESCRIPTOR_H
