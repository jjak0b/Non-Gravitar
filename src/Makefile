NonGravitar: main.o GameEngine.o Viewport.o Vector.o Point.o Point2D.o Bitmap.o ColoredBitmap.o PrintableBitmap.o Entity.o Level.o PlanetEntity.o PlanetLevel.o SolarSystem.o DamageableEntity.o Bunker.o BunkerA.o BunkerB.o BunkerC.o Fuel.o Player.o Projectile.o Shape.o PlayerShape.o SurfaceShape.o BunkerAShape.o BunkerBShape.o BunkerCShape.o Side.o SmallFuel.o BigFuel.o SmallFuelShape.o BigFuelShape.o
	g++ -o NonGravitar main.o GameEngine.o Viewport.o Vector.o Point.o Point2D.o Bitmap.o ColoredBitmap.o PrintableBitmap.o Entity.o Level.o PlanetEntity.o PlanetLevel.o SolarSystem.o DamageableEntity.o Bunker.o BunkerA.o BunkerB.o BunkerC.o Fuel.o Player.o Projectile.o Shape.o PlayerShape.o SurfaceShape.o BunkerAShape.o BunkerBShape.o BunkerCShape.o Side.o SmallFuel.o BigFuel.o SmallFuelShape.o BigFuelShape.o

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

SolarSystem.o : SolarSystem.cpp SolarSystem.hpp
	g++ -c SolarSystem.cpp

PlanetLevel.o : PlanetLevel.cpp PlanetLevel.hpp
	g++ -c PlanetLevel.cpp

PlanetEntity.o : PlanetEntity.cpp PlanetEntity.hpp
	g++ -c PlanetEntity.cpp

DamageableEntity.o: DamageableEntity.cpp DamageableEntity.hpp
	g++ -c DamageableEntity.cpp

Bunker.o: Bunker.cpp Bunker.hpp
	g++ -c Bunker.cpp

BunkerA.o: BunkerA.cpp BunkerA.hpp
	g++ -c BunkerA.cpp

BunkerB.o: BunkerB.cpp BunkerB.hpp
	g++ -c BunkerB.cpp

BunkerC.o: BunkerC.cpp BunkerC.hpp
	g++ -c BunkerC.cpp

Player.o : Player.cpp Player.hpp
	g++ -c Player.cpp

Projectile.o : Projectile.cpp Projectile.hpp
	g++ -c Projectile.cpp

Fuel.o : Fuel.cpp Fuel.hpp
	g++ -c Fuel.cpp

Shape.o : Shape.cpp Shape.hpp
	g++ -c Shape.cpp

Side.o : Side.cpp Side.hpp
	g++ -c Side.cpp

PlayerShape.o : PlayerShape.cpp PlayerShape.hpp
	g++ -c PlayerShape.cpp

SurfaceShape.o : SurfaceShape.cpp SurfaceShape.hpp
	g++ -c SurfaceShape.cpp

BunkerAShape.o : BunkerAShape.cpp BunkerAShape.hpp
	g++ -c BunkerAShape.cpp

BunkerBShape.o : BunkerBShape.cpp BunkerBShape.hpp
	g++ -c BunkerBShape.cpp

BunkerCShape.o : BunkerCShape.cpp BunkerCShape.hpp
	g++ -c BunkerCShape.cpp

SmallFuel.o : SmallFuel.cpp SmallFuel.hpp
	g++ -c SmallFuel.cpp

BigFuel.o : BigFuel.cpp BigFuel.hpp
	g++ -c BigFuel.cpp

SmallFuelShape.o : SmallFuelShape.cpp SmallFuelShape.hpp
	g++ -c SmallFuelShape.cpp

BigFuelShape.o : BigFuelShape.cpp BigFuelShape.hpp
	g++ -c BigFuelShape.cpp


clean:
	del *.o NonGravitar.exe NonGravitar

