/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Argv;

interface ArgumentsConsumable<T> {
  public function valid(): bool;
  public function current(): string;
  public function hasNext(): bool;
  public function next(): string;
  public function consume(): void;
}
