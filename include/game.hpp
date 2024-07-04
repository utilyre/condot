#pragma once

class Game
{
public:
  Game();
  ~Game();

  void Start();

private:
  void Update();
  void Render() const;
};
