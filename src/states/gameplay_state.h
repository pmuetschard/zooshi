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

#ifndef ZOOSHI_GAMEPLAY_STATE_H_
#define ZOOSHI_GAMEPLAY_STATE_H_

#include "camera.h"
#include "corgi/entity_manager.h"
#include "fplbase/input.h"
#include "gpg_manager.h"
#include "pindrop/pindrop.h"
#include "states/state_machine.h"
#include "world.h"

namespace scene_lab {

class SceneLab;

}  // scene_lab

namespace fpl {

class Renderer;
class InputSystem;

namespace zooshi {

struct InputConfig;
class WorldRenderer;
class FullScreenFader;

class GameplayState : public StateNode {
 public:
  GameplayState() : previous_lap_(0), percent_(0.0f) {}
  virtual ~GameplayState() {}

  void Initialize(fplbase::InputSystem* input_system, World* world,
                  const Config* config, const InputConfig* input_config,
                  corgi::EntityManager* entitiy_manager,
                  scene_lab::SceneLab* scene_lab, GPGManager* gpg_manager,
                  pindrop::AudioEngine* audio_engine, FullScreenFader* fader);

  virtual void AdvanceFrame(int delta_time, int* next_state);
  virtual void RenderPrep(fplbase::Renderer* renderer);
  virtual void Render(fplbase::Renderer* renderer);
  virtual void HandleUI(fplbase::Renderer* renderer);
  virtual void OnEnter(int previous_state);
  virtual void OnExit(int next_state);

  int* requested_state() { return &requested_state_; }

 protected:
  World* world_;

  const Config* config_;

  const InputConfig* input_config_;

  fplbase::InputSystem* input_system_;

  corgi::EntityManager* entity_manager_;

  Camera main_camera_;
#ifdef ANDROID_HMD
  Camera cardboard_camera_;
#endif

  // This is needed here so that when transitioning into the editor the camera
  // location can be initialized.
  scene_lab::SceneLab* scene_lab_;

  // Used to submit a score to the leaderboard.
  GPGManager* gpg_manager_;

  int requested_state_;

  // The audio engine, so that sound effects can be played.
  pindrop::AudioEngine* audio_engine_;

  // Cache the common sounds that are going to be played.
  pindrop::SoundHandle sound_pause_;

  // This will eventually be removed when there are events to handle this logic.
  // Crossfade between different music tracks based on what lap you're on. The
  // percent value tracks the transitions over time so the transition from one
  // track to the other is smooth.
  pindrop::SoundHandle music_gameplay_lap_1_;
  pindrop::SoundHandle music_gameplay_lap_2_;
  pindrop::SoundHandle music_gameplay_lap_3_;
  pindrop::Channel music_channel_lap_1_;
  pindrop::Channel music_channel_lap_2_;
  pindrop::Channel music_channel_lap_3_;
  int previous_lap_;
  float percent_;

  // Fade the screen.
  FullScreenFader* fader_;
};

}  // zooshi
}  // fpl

#endif  // ZOOSHI_GAMEPLAY_STATE_H_
