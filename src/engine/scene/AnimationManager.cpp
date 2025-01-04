#include "AnimationManager.h"

#include <iostream>

AnimationManager::AnimationManager(Animation& currentAnimation)
    : m_currentAnimation(&currentAnimation), m_currentFrameIdx(0) {}

// ---------- Functions ----------

void AnimationManager::nextFrame() {
    int nextFrame = m_currentFrameIdx + 1;
    if (nextFrame > m_currentAnimation->m_frames.size() - 1)
        m_currentFrameIdx = 0;
    else
        m_currentFrameIdx = nextFrame;
}

void AnimationManager::addAnimation(Animation animation) {
    m_animations.push_back(animation);
}

void AnimationManager::addAnimations(std::vector<Animation> animations) {
    m_animations.insert(m_animations.end(), animations.begin(), animations.end());
}

// ---------- Getters ---------- 

bool AnimationManager::hasCurrentAnimation() {
    return m_currentAnimation;
}

Animation& AnimationManager::getCurrentAnimation() {
    return *m_currentAnimation;
}

AnimatedFrame& AnimationManager::getCurrentFrame() {
    return m_currentAnimation->m_frames.at(m_currentFrameIdx);
}

int AnimationManager::getCurrentFrameIdx() {
    return m_currentFrameIdx;
}

// ---------- Setters ---------- 

void AnimationManager::setCurrentAnimation(Animation& currentAnimation) {
    m_currentFrameIdx = 0;
    m_currentAnimation = &currentAnimation;
}

void AnimationManager::setCurrentAnimationIdx(int idx) {
    m_currentFrameIdx = 0;
    m_currentAnimation = &m_animations.at(idx);
}