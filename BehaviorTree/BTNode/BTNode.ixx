export module Misaka.BehaviorTree.BTNode;

import <string>;
import glm;

namespace Misaka::BehaviorTree {

export enum class BTSTATUS {
    BT_INVALID,
    BT_SUCCESS,
    BT_FAILURE,
    BT_RUNNING,
};

export class BTNode {
public:
    BTNode()          = default;
    virtual ~BTNode() = default;

    virtual void OnBTNodeStart() = 0;
    virtual void OnBTNodeRun()   = 0;
    virtual void OnBTNodeEnd()   = 0;
};

} // namespace Misaka::BehaviorTree