AddCSLuaFile("shared.lua")
include("shared.lua")

-- Run once whenever entity is spawned
function ENT:Initialize()
    self:SetModel("CHANGE ME")
    self:PhysicsInit(SOLID_VPHYSICS)
    self:SetMoveType(MOVETYPE_VPHYSICS)
    self:SetSolid(SOLID_VPHYSICS)
    self:SetUseType(SIMPLE_USE)

    local phys = self:GetPhysicsObject()
    if phys:IsValid() then
        phys:Wake()
    end
end

-- Called whenever a player presses 'E' on an entity
function ENT:Use(activator, caller)
    
end
 
