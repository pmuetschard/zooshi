// Copyright 2015 Google Inc. All rights reserved.
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

#ifndef COMPONENTS_SOUND_H_
#define COMPONENTS_SOUND_H_

#include "components_generated.h"
#include "corgi/component.h"
#include "corgi/entity_manager.h"
#include "pindrop/pindrop.h"

namespace fpl {
namespace zooshi {

// Data for scene object components.
struct SoundData {
  pindrop::Channel channel;
};

class SoundComponent : public corgi::Component<SoundData> {
 public:
  virtual ~SoundComponent() {}

  virtual void Init();
  virtual void InitEntity(corgi::EntityRef& /*entity*/) {}
  virtual void AddFromRawData(corgi::EntityRef& parent, const void* raw_data);
  virtual void CleanupEntity(corgi::EntityRef& entity);
  virtual void UpdateAllEntities(corgi::WorldTime delta_time);

 private:
  pindrop::AudioEngine* audio_engine_;
};

}  // zooshi
}  // fpl

CORGI_REGISTER_COMPONENT(fpl::zooshi::SoundComponent, fpl::zooshi::SoundData)

#endif  // COMPONENTS_SOUND_H_
