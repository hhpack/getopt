<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Argv;

use HHPack\Getopt\Spec\OptionContainer;
use RuntimeException;

/**
 * This class expands command line arguments according to the specification of option.
 */
final class ArgumentsExtractor {

  public function __construct(private OptionContainer $options) {}

  /**
   * Expand the list of options to name and arguments.
   *
   * -d                 -> [ -d ]
   * -fexample.txt      -> [ -f, example.txt ]
   * --file=example.txt -> [ --file. example.txt ]
   * -xyz               -> [ -x, -y, -z ]
   *                    -> [ -x, -y, z ]
   */
  public function extract(Traversable<string> $argv): ImmVector<string> {
    return $this->extractFlagSet($this->extractOptions($argv));
  }

  /**
   * Expand arguments whose names and values are set into names and arguments.
   */
  private function extractOptions(
    Traversable<string> $argv,
  ): ImmVector<string> {
    $arguments = Vector {};

    foreach ($argv as $value) {
      $matches = [];

      if (preg_match('/^(-|--)(\w+)=(.+)$/', $value, &$matches) !== 1) {
        $arguments->add($value);
        continue;
      }
      list($_, $prefix, $name, $value) = $matches;

      $arguments->addAll([$prefix.$name, $value]);
    }

    return $arguments->toImmVector();
  }

  /**
   * Expand the arguments that have multiple options summarized.
   */
  private function extractFlagSet(
    Traversable<string> $argv,
  ): ImmVector<string> {
    $arguments = Vector {};

    foreach ($argv as $value) {
      $matches = [];

      if (preg_match('/^-([A-Za-z]+)$/', $value, &$matches) !== 1) {
        $arguments->add($value);
        continue;
      }
      list($_, $flags) = $matches;

      if (strlen($flags) <= 1) {
        $arguments->add('-'.$flags);
        continue;
      }

      $flagArguments = $this->extractFlagSetValue($flags);
      $arguments->addAll($flagArguments);
    }

    return $arguments->toImmVector();
  }

  /**
   * Extract multiple options.
   *
   * The result after expansion depends on the number of optional arguments.
   *
   * When all options are not taken
   *   -xyz -> [ -x, -y, -z ]
   *
   * When there is an option to take all the arguments
   *   -xyz -> [ -x, -y, z ]
   */
  private function extractFlagSetValue(string $flags): ImmVector<string> {
    $arguments = Vector {};
    $remainFlags = $flags;

    while (strlen($remainFlags) > 0) {
      $flag = substr($remainFlags, 0, 1);
      $shortName = '-'.$flag;

      if ($this->options->hasNoValue($shortName)) { //has options rule?
        $arguments->add($shortName);
        $remainFlags = substr($remainFlags, 1);
        continue;
      } else if ($this->options->hasOneValue($shortName)) { //has args?
        $value = substr($remainFlags, 1);
        $arguments->addAll([$shortName, $value]);
        break;
      } else {
        throw new RuntimeException(
          sprintf('%s is not a valid option', $flag),
        );
      }
    }

    return $arguments->toImmVector();
  }

  public static function fromOptions(OptionContainer $options): this {
    return new static($options);
  }

}
