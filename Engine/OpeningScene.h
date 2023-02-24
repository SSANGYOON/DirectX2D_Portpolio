#pragma once
#include "syScene.h"
namespace sy
{
    class OpeningScene : public Scene
    {
	public:
		OpeningScene();
		virtual ~OpeningScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		virtual void Exit() override;
    };
}

