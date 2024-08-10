AddCSLuaFile("shared.lua")
include("shared.lua")

-- Run when SWEP is first initialized at server start
function SWEP:Initialize()

	-- Default stance when holding SWEP
	self:SetHoldType("passive")

end

-- Run when SWEP is deployed
function SWEP:Deploy()

end

-- Called when the left mouse button is pressed
function SWEP:PrimaryAttack()

	-- Stops from being called multiple times per use
	if not(IsFirstTimePredicted()) then
		return
	end

    self:SetNextPrimaryFire(CurTime() + 0.5)

end

SWEP:SecondaryAttack()

    -- Stops from being called multiple times per use
	if not(IsFirstTimePredicted()) then
		return
	end

    self:SetNextSecondaryFire(CurTime() + 0.5)

end