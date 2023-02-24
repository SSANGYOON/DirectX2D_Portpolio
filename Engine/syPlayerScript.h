#pragma once
#include "syScript.h"


namespace sy
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Start() override;
		virtual void Update() override;
		virtual void Render() override;

	private:

	};
}
