#pragma once

struct TargetComponent
{
	float ThreatLevel;

	TargetComponent(float threat)
		: ThreatLevel{threat}
	{}

	TargetComponent()
		: ThreatLevel{0.0f}
	{}

};