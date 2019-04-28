NonGravitar: main.o GameEngine.o Viewport.o Vector.o Point.o Point2D.o Bitmap.o ColoredBitmap.o PrintableBitmap.o Entity.o Level.o Planet.o SolarSystem.o DamageableEntity.o Player.o Projectile.o
	g++ -o NonGravitar main.o GameEngine.o Viewport.o Vector.o Point.o Point2D.o Bitmap.o ColoredBitmap.o PrintableBitmap.o Entity.o Level.o Planet.o SolarSystem.o DamageableEntity.o Player.o Projectile.o

main.o: main.cpp GameConfig.h GameEngine.hpp
	g++ -c main.cpp

Bitmap.o: Bitmap.cpp Bitmap.hpp
	g++ -c Bitmap.cpp

ColoredBitmap.o: ColoredBitmap.cpp ColoredBitmap.hpp
	g++ -c ColoredBitmap.cpp

PrintableBitmap.o : PrintableBitmap.cpp PrintableBitmap.hpp
	g++ -c PrintableBitmap.cpp

GameEngine.o : GameEngine.cpp GameEngine.hpp
	g++ -c GameEngine.cpp

Viewport.o : Viewport.cpp Viewport.hpp
	g++ -c Viewport.cpp

Vector.o : Vector.cpp Vector.hpp
	g++ -c Vector.cpp

Point.o : Point.cpp Point.hpp
	g++ -c Point.cpp

Point2D.o : Point2D.cpp Point2D.hpp
	g++ -c Point2D.cpp

Entity.o : Entity.cpp Entity.hpp
	g++ -c Entity.cpp

Level.o : Level.cpp level.hpp
	g++ -c Level.cpp

Planet.o : Planet.cpp Planet.hpp
	g++ -c Planet.cpp

SolarSystem.o : SolarSystem.cpp SolarSystem.hpp
	g++ -c SolarSystem.cpp

DamageableEntity.o: DamageableEntity.cpp DamageableEntity.hpp
	g++ -c DamageableEntity.cpp

Player.o : Player.cpp Player.hpp
	g++ -c Player.cpp

Projectile.o : Projectile.cpp Projectile.hpp
	g++ -c Projectile.cpp

Fuel.o : Fuel.cpp Fuel.hpp
	g++ -c Fuel.cpp

clean:
	del *.o NonGravitar.exe NonGravitar

