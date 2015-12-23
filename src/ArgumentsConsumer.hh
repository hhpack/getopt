<?hh //strict

namespace hhpack\getopt;

use LogicException;
use IteratorAggregate;

final class ArgumentsConsumer implements IteratorAggregate<string>
{

    private int $position = 0;
    private ImmVector<string> $argv;

    public function __construct(
        ArgumentOptions $options,
        Traversable<string> $argv = []
    )
    {
        $extractor = new ArgumentsExtractor($options, $argv);
        $this->argv = ImmVector::fromItems($extractor->items());
    }

    public function valid() : bool
    {
        return $this->argv->count() > $this->position;
    }

    public function current() : string
    {
        return $this->argv->at($this->position);
    }

    public function hasNext() : bool
    {
        $nextAt = $this->position + 1;
        return $this->argv->count() > $nextAt;
    }

    public function next() : string
    {
        if (!$this->hasNext()) {
            throw new LogicException('There is no next value');
        }

        $nextAt = $this->position + 1;
        return $this->argv->at($nextAt);
    }

    public function getIterator() : KeyedIterator<int, string>
    {
        return $this->argv->getIterator();
    }

    public function consume() : void
    {
        $this->position++;
    }

}
