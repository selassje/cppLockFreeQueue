#include "../lfQueue/lfQueue.hpp"

#include <cstddef>

namespace lfQueue
{
	namespace tests
	{
		bool basicTestCase1()
		{
			lfQueue<int> queue;
			queue.push(3);
			return queue.size() == 1;
		}
	}
};