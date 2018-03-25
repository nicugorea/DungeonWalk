#include "includes.h"
#include "Util.h"
#include "Map.h"  
#include "Player.h"


int main(){
	Util util;
	Map map;
	Info info;
	if(!map.LoadFromFile( "res/map.txt" )) LOGLN( "Fail to load from file!" );
	map.Draw();
	map.GetInfo( info );

	Player player( map.GetPlayerPosition() );
	player.GetInfo( info );

	while(!info.stop)
	{
		player.EventHandle(info);
		map.EventHandle( info );
		if(info.needUpdate)
		{
			player.GetInfo( info );
			map.GetInfo( info );

			info.needUpdate = false;
		}
	
	}
	Util::MoveTo( info.mapSize.x*CELL_W+2, 4 );
	LOG( "Game Over" );
	getch();
	return 0;
}