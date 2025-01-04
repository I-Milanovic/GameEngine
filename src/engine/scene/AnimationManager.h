#pragma once

#include "src/engine/scene/Animation.h"

class AnimationManager {

public:
	AnimationManager() = default;
	AnimationManager(Animation& currentAnimation);


	// ---------- Functions ---------- 

	void nextFrame();
	void addAnimation(Animation animation);
	void addAnimations(std::vector<Animation> animations);

	// ---------- Getters ---------- 

	bool hasCurrentAnimation();
	Animation& getCurrentAnimation();
	AnimatedFrame& getCurrentFrame();
	int getCurrentFrameIdx();

	// ---------- Setters ---------- 

	void setCurrentAnimation(Animation& currentAnimation);
	void setCurrentAnimationIdx(int idx);

private:
	std::vector<Animation> m_animations;
	Animation* m_currentAnimation{ nullptr };
	int m_currentFrameIdx{ 0 };

};