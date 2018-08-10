#ifndef INC_2050_JNI_HPP
#define INC_2050_JNI_HPP

#include <string>
#include <vector>

#include <jni.h>

void game_over(int score, bool new_high_score);
void game_win(int score, bool new_high_score);
void game_pause();
std::string get_res_string(const std::string & id);
std::vector<int> get_res_int_array(const std::string & id);

#endif //INC_2050_JNI_HPP
