
function _isPrime( num: number ) : boolean
{

	if( num == 2 )
	{
		return true;
	}

	let limit: number = Math.ceil( Math.sqrt( num ) ) + 1;
	for( let i:number = 2; i<limit; i++ )
	{
		if( num % i == 0 )
		{
			return false;
		}
	}

	return true;
}

function containsZero( s:string): boolean
{
	return s.indexOf("0") != -1;
}

function isTruncatableLR( n:number ): boolean
{
	let s:string = "" + n;

	while( s.length >= 1 )
	{
		if( !_isPrime(parseInt(s)) )
		{
			return false;
		}
		if( s.length == 1 )
		{
			s = "";
		}
		else
		{
			s = s.substring( 1 );
		}
	}

	return true;
}

function isTruncatableRL( n:number ): boolean
{
	let s:string = "" + n;

	while( s.length >= 1 )
	{
		if( !_isPrime(parseInt(s)) )
		{
			return false;
		}
		if( s.length == 1 )
		{
			s = "";
		}
		else
		{
			s = s.substring( 0, s.length - 1 );
		}
	}

	return true;
}

function solve1():number
{
	let sum:number = 0;
	for( let i:number=1000; i<=9999; i++ )
	{
		if( _isPrime( i ) &&
			!containsZero( "" + i ) &&
			isTruncatableLR( i ) &&
			isTruncatableRL( i ) )
		{
			sum += i;
			console.log( i );
		}

	}
	return sum;
}

console.log( solve1() );

function sortString( s: string ) : string
{
	return s.split("").sort().join("");//.replace(/\,/g, "");//replaceAll(",","");
}

function isPandigital( s: string) : boolean
{

	if( s.length != 9 )
	{
		return false;
	}

	s = sortString( s );
	if( s != "123456789" )
	{
		return false;
	}

	return true;
}

function solve2() : number
{
	let max: number = 0;

	for( let n:number=2; n<=9; n++ )
	{
		for( let i:number=1; i<Math.pow(10,9/n); i++ )
		{
			let concat:string = "";
			for( let j:number=1; j<=n; j++ )
			{
				concat += (""+(j*i))
			}
			if( isPandigital( concat ) )
			{
				max = Math.max( parseInt( concat ), max );
			}
		}
	}
	return max;
}

console.log( solve2() );

function triangleSolutions( n:number ):number
{
	let count:number = 0;

	for( let a:number=1; a<=n; a++ )
	{
		for( let b:number = a; b<=n; b++ )
		{

			for( let c:number=b+1; c<=n; c++ )
			{
				if( a + b + c != n )
				{
					continue;
				}

				if( a ** 2 + b ** 2 != c ** 2 )
				{
					continue;
				}

				count++;
			}
		}
	}

	return count;
}

console.log( triangleSolutions(120) );

