#pragma once

UENUM(BlueprintType)
enum class EAuraAttributeImportance : uint8
{
	Vital,
	Primary,
	Secondary,
};

UENUM(BlueprintType)
enum class EAuraAttributeTypes : uint8
{
	HealthPoint UMETA(
		Importance = "Vital",
		TagDevComment = "Character most important Attribute, if less or equal zero, character will die"
	),
	ManaPoint UMETA(
		Importance = "Vital",
		TagDevComment = "Character need this resource to cast spell"
	),

	Strength UMETA(
		Importance = "Primary",
		TagDevComment = "Increase character physical damage"
	),
	Intelligence UMETA(
		Importance = "Primary",
		TagDevComment = "Increase character magic damage"
	),
	Resilience UMETA(
		Importance = "Primary",
		TagDevComment = "Increase character's armor and other resistance chance, like critical resistance"
	),
	Vigor UMETA(
		Importance = "Primary",
		TagDevComment = "Increase character's HP and HP Regeneration"
	),

	Armor UMETA(
		Importance = "Secondary",
		TagDevComment = "Reduce incoming damage, based on Resilience"
	),
	ArmorPenetration UMETA(
		Importance = "Secondary",
		TagDevComment = "Ignores percentage of enemy's armor, based on Resilience"
	),
	BlockChance UMETA(
		Importance = "Secondary",
		TagDevComment = "Reduce incoming damage to half, based on Armor"
	),
	CriticalChance UMETA(
		Importance = "Secondary",
		TagDevComment = "Make damage multiply CriticalDamagePercent , based on ArmorPenetration"
	),
	CriticalDamagePercent UMETA(
		Importance = "Secondary",
		TagDevComment = "When critical happened, how much damage to make, based on ArmorPenetration"
	),
	CriticalResistance UMETA(
		Importance = "Secondary",
		TagDevComment = "Reduce critical chance, based on Armor"
	),
	CriticalDamagePercentResistance UMETA(
		Importance = "Secondary",
		TagDevComment = "Reduce critical damage percentage, based on Armor"
	),
	HealthRegeneration UMETA(
		Importance = "Secondary",
		TagDevComment = "How much health point auto add, per 1 second, based on Vigor"
	),
	ManaRegeneration UMETA(
		Importance = "Secondary",
		TagDevComment = "How much mana point auto add per 1 second, based on Intelligence"
	),
	MaxHealthPoint UMETA(
		Importance = "Secondary",
		TagDevComment = "Character's max Health Point, based on Vigor"
	),
	MaxManaPoint UMETA(
		Importance = "Secondary",
		TagDevComment = "Character's max Mana Point, based on Intelligence"
	),
};
