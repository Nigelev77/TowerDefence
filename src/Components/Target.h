#pragma once

struct TargetComponent
{
	float ThreatLevel;
	float ThreatMultiplier;

	TargetComponent(float threat, float mul)
		: ThreatLevel{threat}, ThreatMultiplier{mul}
	{}

	TargetComponent(float mul)
		: ThreatLevel{0.0f}, ThreatMultiplier{1.0f}
	{}

	TargetComponent()
		: ThreatLevel{0.0f}, ThreatMultiplier{1.0f}
	{}

};