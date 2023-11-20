#pragma once
class Framebuffer {

public:
	void init(int width, int height);
	void bindFrameBuffer();
	void unbindFrameBuffer();
	inline unsigned int getFboId() { return m_fbo; }
	inline unsigned int getColorTex() { return textureColorBuffer; }
private:
	unsigned int m_fbo;
	unsigned int textureColorBuffer;
};
