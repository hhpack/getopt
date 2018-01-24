<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Spec;

abstract class AbstractOption implements Option {

  protected ImmSet<string> $names;
  protected string $helpMessage = '';
  protected int $numberOfArgs = 0;

  public function names(): ImmSet<string> {
    return $this->names;
  }

  public function options(): Iterator<Pair<string, Option>> {
    foreach ($this->names->items() as $name) {
      yield Pair {$name, $this};
    }
  }

  public function isTakesValue(): bool {
    return $this->numberOfArgs > 0;
  }

  public function helpMessage(): string {
    return $this->helpMessage;
  }

  public function toImmMap(): ImmMap<string, Option> {
    return ImmMap::fromItems($this->options());
  }

  protected function matches(string $name): bool {
    $matched = false;

    $nameMatchers =
      ImmVector::fromItems($this->names)->map(
        ($name) ==> {
          return new NameMatcher($name);
        },
      );

    foreach ($nameMatchers->items() as $nameMatcher) {
      if ($nameMatcher->matches($name)) {
        $matched = true;
        break;
      }
    }
    return $matched;
  }
}
