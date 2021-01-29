#include "api/functions/color.hpp"
#include "api/functions/math.hpp"

SDL_Color color(Uint8 r, Uint8 g, Uint8 b){
    return (SDL_Color){r, g, b, 255};
}

SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    return (SDL_Color){r, g, b, a};
}

std::vector<std::string> SplitWithCharacters(const std::string& str, int splitLength) {
  int NumSubstrings = str.length() / splitLength;
  std::vector<std::string> ret;

  for (int i = 0; i < NumSubstrings; i++) {
     ret.push_back(str.substr(i * splitLength, splitLength));
  }

  // If there are leftover characters, create a shorter item at the end.
  if (str.length() % splitLength != 0) {
      ret.push_back(str.substr(splitLength * NumSubstrings));
  }


  return ret;
}

SDL_Color HEXA_to_color(std::string color) {
  SDL_Color out;

  if(color.at(0) == '#') {
      color.erase(0, 1);
  }

  while(color.length() != 6) {
      color += "0";
  }

  std::vector<string> colori=SplitWithCharacters(color,2);

  out.r = stoi(colori[0],nullptr,16);
  out.g = stoi(colori[1],nullptr,16);
  out.b = stoi(colori[2],nullptr,16);

  return out;
}

SDL_Color RGB_To_color(std::string color){
    SDL_Color out = {0, 0, 0, 0};
    return out;
}