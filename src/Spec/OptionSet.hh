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

use LogicException;
use RuntimeException;
use ConstCollection;

final class OptionSet implements OptionCollection {

  private ImmVector<Option> $options;
  private ImmMap<string, Option> $registry;

  public function __construct(Traversable<Option> $options = []) {
    $mappedOptions = Map {};

    foreach ($options as $option) {
      $mappedOptions->setAll($option->toImmMap());
    }

    $this->options = ImmVector::fromItems($options);
    $this->registry = $mappedOptions->toImmMap();
  }

  /**
   * $options->contains('-c');
   * $options->contains('-c', '--config');
   */
  public function contains(...): bool {
    $included = false;
    $optionNames = $this->optionNames();

    foreach (func_get_args() as $name) {
      if (!$optionNames->contains($name)) {
        continue;
      }
      $included = true;
      break;
    }

    return $included;
  }

  /**
   * $options->get('-c');
   * $options->get('--config');
   */
  public function get(string $name): Option {
    if (!$this->registry->containsKey($name)) {
      throw new LogicException('have not option '.$name);
    }
    return $this->registry->at($name);
  }

  public function hasNoValue(string $name): bool {
    return $this->noValues()->containsKey($name);
  }

  <<__Memoize>>
  public function noValues(): ImmMap<string, Option> {
    $selector = ($option) ==> !$option->isTakesValue();
    return $this->registry->filter($selector);
  }

  public function hasOneValue(string $name): bool {
    return $this->oneValues()->containsKey($name);
  }

  public function isEmpty(): bool {
    return $this->registry->isEmpty();
  }

  public function count(): int {
    return $this->registry->count();
  }

  public function items(): Iterable<Option> {
    return $this->options->values();
  }

  <<__Memoize>>
  public function oneValues(): ImmMap<string, Option> {
    $selector = ($option) ==> $option->isTakesValue();
    return $this->registry->filter($selector);
  }

  <<__Memoize>>
  private function optionNames(): ImmSet<string> {
    $optionNames = Set {};

    foreach ($this->registry->values() as $option) {
      $optionNames->addAll($option->names());
    }

    return $optionNames->toImmSet();
  }

  /**
   * Display help message for options
   *
   * Examples:
   *
   *   Options:
   *     -h, -help     help message
   *     -v, -version  version message
   */
  public function displayHelp(): void {
    fwrite(STDOUT, "Options:\n");

    $labels =
      $this->items()->map(
        ($option) ==> {
          return $option->helpLabel();
        },
      )->toArray();

    $maxLength = array_reduce(
      $labels,
      ($current, $label) ==> {
        $maxLength = $current;

        if (strlen($label) > $current) {
          $maxLength = strlen($label);
        }

        return $maxLength;
      },
      0,
    );

    foreach ($this->items() as $option) {
      fwrite(
        STDOUT,
        sprintf(
          "  %s  %s\n",
          str_pad($option->helpLabel(), $maxLength),
          $option->helpMessage(),
        ),
      );
    }
  }

}
