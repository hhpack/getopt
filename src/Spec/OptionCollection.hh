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

use ConstCollection;
use Countable;

interface OptionCollection
  extends Countable, OptionContainer, HelpDisplayable {

  // From ConstCollection<+Te> excluding toDArray / toVArray methods
  public function isEmpty(): bool;
  public function count(): int;
  public function items(): Iterable<Option>;

  public function get(string $name): Option;
  public function contains(...): bool;
  public function noValues(): ImmMap<string, Option>;
  public function oneValues(): ImmMap<string, Option>;
}
