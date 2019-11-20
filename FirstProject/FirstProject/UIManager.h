#pragma once

#include <vector>
#include <glm/glm.hpp> 

class Shader;
class UIElement;

class UIManager
{
public:
	UIManager();
	~UIManager();

	void UpdateManager(float aDeltaTime);
	void RenderManager();

	void UpdateMousePosition(glm::vec2 aNewPosition);
	const glm::vec2 GetMousePosition();

	void UpdateMouseStatus(bool aStatus);
	const bool GetMouseStatus();

	void SetShader(Shader* aShader);

protected:
	virtual void Update(float aDeltaTime);
	virtual void Render(Shader* aShader);

protected:
	std::vector<UIElement> myElements;

	bool myIsActive = true;
	bool myIsHidden = false;

	glm::vec2 myMousePosition = glm::vec2(0.0f);
	bool myMouseStatus = false;

	Shader* myShader;
};

