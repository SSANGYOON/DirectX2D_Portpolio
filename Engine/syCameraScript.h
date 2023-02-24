#pragma once
#include "syScript.h"


namespace sy
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Start() override;
		virtual void Update() override;
		virtual void Render() override;

	private:

	};
}

