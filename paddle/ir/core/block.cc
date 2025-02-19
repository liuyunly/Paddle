// Copyright (c) 2023 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "paddle/ir/core/block.h"
#include "paddle/ir/core/operation.h"
#include "paddle/ir/core/region.h"

namespace ir {
Block::~Block() { clear(); }
void Block::push_back(Operation *op) { insert(ops_.end(), op); }

void Block::push_front(Operation *op) { insert(ops_.begin(), op); }

Operation *Block::GetParentOp() const {
  return parent_ ? parent_->GetParent() : nullptr;
}

Block::iterator Block::insert(const_iterator iterator, Operation *op) {
  Block::iterator iter = ops_.insert(iterator, op);
  op->SetParent(this, iter);
  return iter;
}

void Block::clear() {
  while (!empty()) {
    ops_.back()->Destroy();
    ops_.pop_back();
  }
}

void Block::SetParent(Region *parent, Region::iterator position) {
  parent_ = parent;
  position_ = position;
}

}  // namespace ir
