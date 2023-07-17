#include "tests/helpers.hpp"

using namespace btx::math;
using namespace Catch::Matchers;

TEST_CASE("Am I in front or behind the NPC?", "[vectors][examples]") {
    // The NPC is at the origin, looking "up" along the Y axis
    Vec3 const npc_pos = Vec3::zero;
    Vec3 const npc_fwd = Vec3::unit_y;

    // The player is up and to the right from the NPC, which means they're in
    // front of the NPC
    Vec3 player_pos(1, 1, 0);
    Vec3 npc_to_player = player_pos - npc_pos;
    REQUIRE(dot(npc_fwd, npc_to_player) > 0.0f);

    // Now move the player to be directly behind the NPC
    player_pos = -Vec3::unit_y;
    npc_to_player = player_pos - npc_pos;
    REQUIRE(dot(npc_fwd, npc_to_player) < 0.0f);

    // Finally try putting the player directly right or left of the NPC, which
    // will result in a dot of zero for both positions
    player_pos = Vec3::unit_x;
    npc_to_player = player_pos - npc_pos;
    REQUIRE_THAT(dot(npc_fwd, npc_to_player), WithinAbs(0.0f, epsilon));

    player_pos = -Vec3::unit_x;
    npc_to_player = player_pos - npc_pos;
    REQUIRE_THAT(dot(npc_fwd, npc_to_player), WithinAbs(0.0f, epsilon));
}

TEST_CASE("NPC vision cone", "[vectors][examples]") {
    // The NPC is at the origin, looking "up" along the Y axis, and has a
    // 150-degree horizontal field of view
    Vec3 const npc_pos = Vec3::zero;
    Vec3 npc_fwd = Vec3::unit_y;
    float const cos_half_fov = std::cos(radians(150.0f / 2.0f));

    // If the FOV is super narrow, then it's easier to hide from the NPC
    float const cos_tiny_fov = std::cos(radians(10.0f));

    // The player is up and to the right from the NPC, within the normal FOV
    Vec3 player_pos(1, 1, 0);
    Vec3 npc_to_player = normalize(player_pos - npc_pos);
    REQUIRE(dot(npc_fwd, npc_to_player) >= cos_half_fov);
    REQUIRE(dot(npc_fwd, npc_to_player) < cos_tiny_fov);

    // Move the player to the left of the NPC, but keep them within the NPC's
    // normal vision cone
    player_pos = { -1, 1, 0 };
    npc_to_player = normalize(player_pos - npc_pos);
    REQUIRE(dot(npc_fwd, npc_to_player) >= cos_half_fov);
    REQUIRE(dot(npc_fwd, npc_to_player) < cos_tiny_fov);

    // If the player is directly to the left or right of the NPC, the dot of
    // our two vectors will still yield zero, but falling outside of the NPC's
    // vision cone means this check will fail in the same way as the others
    player_pos = Vec3::unit_x;
    npc_to_player = normalize(player_pos - npc_pos);
    REQUIRE(dot(npc_fwd, npc_to_player) < cos_half_fov);

    player_pos = -Vec3::unit_x;
    npc_to_player = normalize(player_pos - npc_pos);
    REQUIRE(dot(npc_fwd, npc_to_player) < cos_half_fov);

    // The player somehow sneaks directly behind the NPC
    player_pos = -Vec3::unit_y;
    npc_to_player = normalize(player_pos - npc_pos);
    REQUIRE(dot(npc_fwd, npc_to_player) < cos_half_fov);

    // Flip the NPC's view direction around, and suddenly the player is smack
    // in the center of the NPC's view. The player is also now within the tiny
    // FOV.
    npc_fwd = -Vec3::unit_y;
    REQUIRE(dot(npc_fwd, npc_to_player) >= cos_half_fov);
    REQUIRE(dot(npc_fwd, npc_to_player) >= cos_tiny_fov);
}

TEST_CASE("Finding the normal to a surface", "[vectors][examples]") {
    // Three points which can define the XY plane
    Vec3 a(1.0f, 1.0f, 0.0f);
    Vec3 b(-3.0f, 6.0f, 0.0f);
    Vec3 c(0.0f, -2.0f, 0.0f);

    // And the normal to that plane is the Z unit vector
    Vec3 normal = normalize(cross(b - a, c - a));
    REQUIRE(normal == Vec3::unit_z);

    // Define the XZ plane with similar points
    a = { 1.0f, 0.0f, 1.0f };
    b = { 0.0f, 0.0f, -2.0f };
    c = { -3.0f, 0.0f, 6.0f };

    // And the normal to that plane is the Y unit vector
    normal = normalize(cross(b - a, c - a));
    REQUIRE(normal == Vec3::unit_y);

    // Finally, the YZ plane
    a = { 0.0f, 1.0f, 1.0f };
    b = { 0.0f, -3.0f, 6.0f };
    c = { 0.0f, 0.0f, -2.0f };

    // And the normal to that plane is the X unit vector
    normal = normalize(cross(b - a, c - a));
    REQUIRE(normal == Vec3::unit_x);
}