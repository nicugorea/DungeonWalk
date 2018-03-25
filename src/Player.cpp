#include "Player.h"
#include "Util.h"



Player::Player( const Point& _pos )
{
	pos = _pos;
}


Player::~Player()
{
}

bool Player::FindPath( int** _map, const Point& _size )
{
	path.clear();
	int width = _size.x;
	int height = _size.y;

	Node** table = new Node*[height];

	for(int i = 0; i < _size.y; i++)
		table[i] = new Node[width];


	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			table[i][j].id = _map[i][j];
			table[i][j].point = { j,i };
			table[i][j].visited = false;
			table[i][j].looking = false;
		}
	}


	std::deque<Node> toSee;
	table[pos.y][pos.x].parent = { -1,-1 };
	toSee.push_back( table[pos.y][pos.x] );

	int px = 0, py = 0;
	int count = 0;
	while(!toSee.empty())
	{
		Node current = toSee.front();
		table[current.point.y][current.point.x].visited = true;
		if(current.id == -1)
		{
			px = current.point.x;
			py = current.point.y;
			break;
		}
		if(current.point.x > 0)
		{
			Node *tmp = &table[current.point.y][current.point.x - 1];
			if(!tmp->looking && !tmp->visited && tmp->id <= 0)
			{
				tmp->looking = true;
				tmp->parent = current.point;
				toSee.push_back( *tmp );
			}

		}
		if(current.point.x < width - 1)
		{
			Node *tmp = &table[current.point.y][current.point.x + 1];
			if(!tmp->looking && !tmp->visited && tmp->id <= 0)
			{
				tmp->looking = true;
				tmp->parent = current.point;
				toSee.push_back( *tmp );
			}

		}
		if(current.point.y < height - 1)
		{
			Node *tmp = &table[current.point.y + 1][current.point.x];
			if(!tmp->looking && !tmp->visited && tmp->id <= 0)
			{
				tmp->looking = true;
				tmp->parent = current.point;
				toSee.push_back( *tmp );
			}

		}
		if(current.point.y > 0)
		{
			Node *tmp = &table[current.point.y - 1][current.point.x];
			if(!tmp->looking && !tmp->visited && tmp->id <= 0)
			{
				tmp->looking = true;
				tmp->parent = current.point;
				toSee.push_back( *tmp );
			}

		}




		/*  Show what can see
	  for(int i = 0; i < height; i++)
	  {

		  for(int j = 0; j < width; j++)
		  {

			  if(table[i][j].visited)
			  {
				  Util::MoveTo( table[i][j].point.x*CELL_W + 1, table[i][j].point.y*CELL_H + 1 );
				  LOG( "V" );
			  }
			  else if(table[i][j].looking)
			  {
				  Util::MoveTo( table[i][j].point.x*CELL_W + 1, table[i][j].point.y*CELL_H + 1 );
				  LOG( "L" );
			  }
		  }
	  }





	  _sleep( 100 );
	  */
		toSee.pop_front();

	}
	Node tmp = table[py][px];
	while(true)
	{
		path.push_back( tmp.point );
		if(tmp.point.x == pos.x && tmp.point.y == pos.y)
			break;
		tmp = table[tmp.parent.y][tmp.parent.x];



	}



	return false;
}

void Player::DrawPath()
{
	for(int i = path.size() - 1; i >= 0; i--)
	{
		Util::MoveToCell( path[i] );
		Util::MoveWith( -1, 0 );
		LOG( "C" );
	}
}

void Player::ErasePath()
{
	for(int i = path.size() - 1; i >= 0; i--)
	{
		Util::MoveToCell( path[i] );
		Util::MoveWith( -1, 0 );
		LOG( " " );
	}
}

void Player::Draw()
{
	Util::MoveToCell( pos );
	LOG( skin );
}

void Player::DrawScore( Info& _info )
{
	Util::MoveTo( _info.mapSize.x*CELL_W + 9, 2 );
	LOG( "Score:         " );
	Util::MoveTo( _info.mapSize.x*CELL_W + 9, 2 );
	LOG( "Score: " << score );

}

void Player::Erase()
{
	Util::MoveToCell( pos );
	LOG( " " );
}

void Player::Move( const char _direction )
{
	Erase();
	if(_direction == 'u')
		pos.y--;
	else if(_direction == 'd')
		pos.y++;
	else if(_direction == 'l')
		pos.x--;
	else if(_direction == 'r')
		pos.x++;
	Draw();
	score = score MOVE_SCORE;
}

void Player::GetInfo( Info & _info )
{
	FindPath( _info.map, _info.mapSize );
	_info.path = GetPath();
}

void Player::EventHandle( Info &_info )
{
	Point last = pos;
	//### Check for moves from arrow keys
	if(GetAsyncKeyState( VK_UP ))
	{
		direction = 'u';
		skin = 202;
		if(pos.y > 0
			&& _info.map[pos.y - 1][pos.x] < 1)
			Move( 'u' );
	}
	if(GetAsyncKeyState( VK_DOWN ))
	{
		direction = 'd';
		skin = 203;
		if(pos.y < _info.mapSize.y - 1
			&& _info.map[pos.y + 1][pos.x] < 1)
			Move( 'd' );
	}
	if(GetAsyncKeyState( VK_RIGHT ))
	{
		direction = 'r';
		skin = 204;
		if(pos.x < _info.mapSize.x - 1
			&& _info.map[pos.y][pos.x + 1] < 1)
			Move( 'r' );
	}
	if(GetAsyncKeyState( VK_LEFT ))
	{
		direction = 'l';
		skin = 185;
		if(pos.x > 0
			&& _info.map[pos.y][pos.x - 1] < 1)
			Move( 'l' );
	}

	//### Check for moves from random ai
	if(random)
		RandomMove( _info );

	_info.playerPos = pos;
	if(GetAsyncKeyState( VK_SPACE ))
	{
		score = score SHOT_SCORE;
		Point cell = pos;
		if(direction == 'r')
			cell.x++;
		if(direction == 'l')
			cell.x--;
		if(direction == 'd')
			cell.y++;
		if(direction == 'u')
			cell.y--;

		if(_info.map[cell.y][cell.x] == -2)
		{
			_info.map[cell.y][cell.x] = 0;
			Util::MoveToCell( cell );
			LOG( " " );
			score = score KLL_SCORE;
		}

	}

	//### Check for path
	if(GetAsyncKeyState( 0x58 ))//x key
	{
		if(_info.pathState)
			_info.pathState = false;
		else
			_info.pathState = true;
	}

	if(_info.pathState && (pos.x != last.x || pos.y != last.y))
	{
		ErasePath();
		FindPath( _info.map, _info.mapSize );
		DrawPath();
		pathOn = true;
	}
	else if(!_info.pathState)
	{
		ErasePath();
		pathOn = false;
	}


	if(GetAsyncKeyState( 0x52 ))//r key
		if(random)
		{
			random = false;
		}
		else
		{
			random = true;
		}

	if(_info.map[pos.y][pos.x] == -1)
	{
		_info.stop = true;
		score = score TREASURE_SCORE;
	}
	else if(_info.map[pos.y][pos.x] == -2)
	{
		score = score MONSTER_SCORE;
		_info.map[pos.y][pos.x] = 0;

	}
	Draw();
	DrawScore( _info );
	_sleep( 150 );
}

void Player::RandomMove( Info& _info )
{
	char dirs[] = { 'u','d','l','r' };

	direction = dirs[rand() % 4];

	
		if(direction == 'u')
		{
			skin = 202;
			if(pos.y > 0
				&& _info.map[pos.y - 1][pos.x] < 1)
				Move( 'u' );

		}
		if(direction == 'd')
		{
			skin = 203;
			if(pos.y < _info.mapSize.y - 1
				&& _info.map[pos.y + 1][pos.x] < 1)
				Move( 'd' );

		}
		if(direction == 'l')
		{
			skin = 185;
			if(pos.x > 0
				&& _info.map[pos.y][pos.x - 1] < 1)
				Move( 'l' );

		}
		if(direction == 'r')
		{
			skin = 204;
			if(pos.x < _info.mapSize.x - 1
				&& _info.map[pos.y][pos.x + 1] < 1)
				Move( 'r' );

		}

	



}

