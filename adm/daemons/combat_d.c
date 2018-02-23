/* command_d.c
 *
 * Emraef @ GBmud
 * 22-SEP-11
 * Command daemon.
 *
 * Contributors: Emraef
 *
 *************************************************************/

int handleCombatAttack( object hitData );
int applyHitToTarget( object target, object hitData );

int handleCombatAttack( object hitData )
{
   if( hitData->GetAttackType() == 0 )
   {
       if( applyHitToTarget( hitData->GetVictim(), hitData ) )
       {
           tell_object( hitData->GetVictim(), hitData->GetHitText() );
       }
   }
}

int handleCombatResult( object hitData )
{

}



int applyHitToTarget( object target, object hitData )
{
    int damage;
    string defenseSkill;
    int defenseDiff;
    int skillTestDifference;

    damage = hitData->GetDamage();
    defenseSkill = hitData->GetSuggestedDefense();
    defenseDiff = hitData->GetDefenseDifficulty();

    skillTestDifference = target->DoSkillRoll( defenseSkill, defenseDiff );

    if( skillTestDifference <= 0 )
    {
        return 0;
    }

    damage *= ceil( skillTestDifference/10.0 ); 
    target->CauseDamage( damage );
}
