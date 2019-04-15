/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Argv;

use LogicException;
use IteratorAggregate;

final class ArgumentsConsumer
  implements ArgumentsConsumable<string>, IteratorAggregate<string> {

  private int $position = 0;
  private ImmVector<string> $argv;

  public function __construct(Traversable<string> $extractedArgv = []) {
    $this->argv = ImmVector::fromItems($extractedArgv);
  }

  public function valid(): bool {
    return $this->argv->count() > $this->position;
  }

  public function current(): string {
    return $this->argv->at($this->position);
  }

  public function hasNext(): bool {
    $nextAt = $this->position + 1;
    return $this->argv->count() > $nextAt;
  }

  public function next(): string {
    if (!$this->hasNext()) {
      throw new LogicException('There is no next value');
    }

    $nextAt = $this->position + 1;
    return $this->argv->at($nextAt);
  }

  public function getIterator(): KeyedIterator<int, string> {
    return $this->argv->getIterator();
  }

  public function consume(): void {
    $this->position++;
  }

  public function applyTo<T as \OutputCollection<string>>(T $args): T {
    while ($this->valid()) {
      $args->add($this->current());
      $this->consume();
    }

    return $args;
  }

}
