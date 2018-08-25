#include <cstddef>

#include "../lfQueue/lfQueue.hpp"

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