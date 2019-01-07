#include "collision_detection.h"
#include "sound_manager.h"
#include <iostream>
namespace game
{
bool CollisionDetection::detect_movement(LevelManager* level_manager, PlayableCharacter* character) {
    level_manager_ = level_manager;
    character_ = character;
    bool reached_goal{false};
    if (level_manager_ && character_) {
        create_collision_zone();
        handle_leaving_level();

        // Iterate through all local blocks
        for (int x = start_zone_.x; x < end_zone_.x; ++x) {
            for (int y = start_zone_.y; y < end_zone_.y; ++y) {
                set_current_block(Vector2i{x, y});
                fire_and_water_block();
                regular_block();
                reached_goal = endgame_block();
            }
        }
    } else {
        std::cerr << "CollisionDetection: LevelManager or Character is nullptr" << std::endl;
    }
    return reached_goal;
}

void CollisionDetection::detect_characters_overlaping(Thomas& thomas, Bob& bob) {
    if (bob.get_feet().intersects(thomas.get_head()))
        bob.stop_falling(thomas.get_head().top);
    else if (thomas.get_feet().intersects(bob.get_head()))
        thomas.stop_falling(bob.get_head().top);
}

void CollisionDetection::create_collision_zone() {
    FloatRect zone{character_->get_position()};

    start_zone_ = Vector2i{static_cast<int>(zone.left / kTileSize) - 1, static_cast<int>(zone.top / kTileSize) - 1};
    end_zone_ = Vector2i{static_cast<int>(zone.left / kTileSize) + 2, static_cast<int>(zone.top / kTileSize) + 3};
}

void CollisionDetection::handle_leaving_level() {
    // Make sure we don't test positions outside the screen
    if (start_zone_.x < 0) start_zone_.x = 0;
    if (start_zone_.y < 0) start_zone_.y = 0;
    if (end_zone_.x >= static_cast<int>(level_manager_->get_level_size().x)) end_zone_.x = level_manager_->get_level_size().x;
    if (end_zone_.y >= static_cast<int>(level_manager_->get_level_size().y)) end_zone_.y = level_manager_->get_level_size().y;

    // Has this character fallen out of the map?
    FloatRect level(0.f, 0.f, level_manager_->get_level_size().x * kTileSize, level_manager_->get_level_size().y * kTileSize);
    if (not character_->get_position().intersects(level)) character_->spawn(level_manager_->get_start_pos(), kGravity);
}

void CollisionDetection::set_current_block(Vector2i coords) {
    current_block_.left = coords.x * kTileSize;
    current_block_.top = coords.y * kTileSize;
    current_block_type_ = static_cast<BlockType>(level_manager_->get_array_level()[coords.y][coords.x]);
}

void CollisionDetection::regular_block() {
    // Check if it's a regular block
    if (current_block_type_ == BlockType::REGULAR) {
        if (character_->get_right().intersects(current_block_))
            character_->stop_right(current_block_.left);
        else if (character_->get_left().intersects(current_block_))
            character_->stop_left(current_block_.left);

        if (character_->get_feet().intersects(current_block_))
            character_->stop_falling(current_block_.top);
        else if (character_->get_head().intersects(current_block_))
            character_->stop_jump();
    }
}

void CollisionDetection::fire_and_water_block() {
    // Check if block is fire or water
    if (current_block_type_ == BlockType::FIRE || current_block_type_ == BlockType::WATER) {
        if (character_->get_head().intersects(current_block_)) {
            character_->spawn(level_manager_->get_start_pos(), kGravity);
            if (current_block_type_ == BlockType::FIRE) {
                SoundManager::get_instance().play_sound(SoundType::FALL_IN_FIRE);
                SoundBuffer buffer;
                buffer.loadFromFile("res/sound/fallinfire.wav");
                Sound sound{buffer};
                sound.play();
            } else
                SoundManager::get_instance().play_sound(SoundType::FALL_IN_FIRE);
        }
    }
}

bool CollisionDetection::endgame_block() {
    // Check if it's end-game block
    if (current_block_type_ == BlockType::ENDGAME)
        return true;
    else
        return false;
}
} // namespace game
