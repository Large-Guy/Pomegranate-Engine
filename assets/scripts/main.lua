player = Entity(1) -- Create a new entity

player:add("Player", {
    name = "Player 1",
    health = 100,
    mana = 100,
    speed = 10,
}) -- Add a lua component

player:add("Weapon",{
    damage = 10,
    range = 10,
    attackSpeed = 1,
})

Debug.Log.info("Player Name:",player.Player.name) -- Print the name of the player
Debug.Log.info("Player Health:",player.Player.health) -- Print the health of the player
Debug.Log.info("Player Mana:",player.Player.mana) -- Print the mana of the player
Debug.Log.info("Player Speed:",player.Player.speed) -- Print the speed of the player

Debug.Log.info("Player Damage:",player.Weapon.damage) -- Print the damage of the player
Debug.Log.info("Player Range:",player.Weapon.range) -- Print the range of the player
Debug.Log.info("Player Attack Speed:",player.Weapon.attackSpeed) -- Print the attack speed of the player

Debug.Log.info("Player Rotation:", player.Transform2D.rotation) -- Print the rotation of the player