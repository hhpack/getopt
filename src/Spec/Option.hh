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

use HHPack\Getopt\Argv\ArgumentsConsumable;

interface Option
{
    public function names() : ImmSet<string>;
    public function options() : Iterator<Pair<string, Option>>;
    public function helpLabel() : string;
    public function helpMessage() : string;
    public function isTakesValue() : bool;
    public function consume(ArgumentsConsumable<string> $consumer) : void;
    public function toImmMap() : ImmMap<string, Option>;
}
