#include "Dynamics.h"
#include "bgeMath.h"

bool CBoundingSphere::Hit(CDynamics *target)
{
	switch(target->Type())
	{
	case DT_SPHERE:		// ‹…‘Î‹…
		return ((r + ((CBoundingSphere*)target)->r) > MathDirection(c, ((CBoundingSphere*)target)->c));
	}
	return false;
}
