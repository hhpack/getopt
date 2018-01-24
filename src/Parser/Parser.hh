<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Parser;

interface Parser {
  /**
   * Parse command line arguments
   */
  public function parse(Traversable<string> $input): ImmVector<string>;
}
