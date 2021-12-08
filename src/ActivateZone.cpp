#include "Config.h"
#include "ScriptMgr.h"

class ActiveCreature : public DataMap::Base
{
    public:
        ActiveCreature() {}
        ActiveCreature(bool isActive) : isActive(isActive) {}
        bool isActive = false;
};

class ActivateZone : public AllCreatureScript
{
    public:
        ActivateZone() : AllCreatureScript("ActivateZone") {}

        void OnAllCreatureUpdate(Creature* creature, uint32 diff) override
        {
            SetActiveCreature(creature);
        }

    private:
        void SetActiveCreature(Creature* creature)
        {
            if (!creature)
                return;

            if (creature->GetMapId() != 0 && creature->GetMapId() != 1 && creature->GetMapId() != 530 && creature->GetMapId() != 571)
                return;

            if (!creature->GetZoneId())
                return;

            if (sWorld->FindPlayerInZone(creature->GetZoneId()))
            {
                if (!creature->CustomData.GetDefault<ActiveCreature>("ActiveCreature")->isActive)
                {
                    creature->CustomData.Set("ActiveCreature", new ActiveCreature(creature->GetGUID()));
                    creature->setActive(true);
                    //LOG_INFO("server.loading", "Creature %s (zone: %u) is now active", creature->GetName().c_str(), creature->GetZoneId());
                }
            }
            else
            {
                if (creature->CustomData.GetDefault<ActiveCreature>("ActiveCreature")->isActive)
                {
                    creature->CustomData.GetDefault<ActiveCreature>("ActiveCreature")->isActive = false;
                    creature->setActive(false);
                    //LOG_INFO("server.loading", "Creature %s (zone: %u) is no longer active", creature->GetName().c_str(), creature->GetZoneId());
                }
            }
        }
};

void AddActivateZonesScripts()
{
    new ActivateZone();
}
