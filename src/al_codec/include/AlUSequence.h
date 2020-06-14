/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWVC_ANDROID_ALUSEQUENCE_H
#define HWVC_ANDROID_ALUSEQUENCE_H

#include "Unit.h"
#include "AlMediaTrack.h"
#include "AlIdentityCreator.h"

al_def_unit(AlUSequence, Unit) {
public:
    AlUSequence(const std::string alias);

    virtual ~AlUSequence();

    virtual bool onCreate(AlMessage *msg) override;

    virtual bool onDestroy(AlMessage *msg) override;

private:
    bool _onHeartbeat(AlMessage *msg);

    bool _onAddTrack(AlMessage *msg);

private:
    AlIdentityCreator creator;
    std::map<int32_t, std::unique_ptr<AlMediaTrack>> tracks;
};


#endif //HWVC_ANDROID_ALUSEQUENCE_H