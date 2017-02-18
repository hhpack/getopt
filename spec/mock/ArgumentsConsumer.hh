<?hh //strict

namespace HHPack\Getopt\Spec\Mock;

use HHPack\Getopt\Argv\ArgumentsConsumable;
use LogicException;

final class ArgumentsConsumer implements ArgumentsConsumable<string>
{

    private int $position = 0;
    private ImmVector<string> $argv;

    public function __construct(
        Traversable<string> $argv
    )
    {
        $this->argv = ImmVector::fromItems($argv);
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

    public function consume() : void
    {
        $this->position++;
    }

}
