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

interface Option<+T> extends Matcher
{
    public function name() : string;
    public function flags() : ImmSet<string>;
    public function options() : Iterator<Pair<string, Option<T>>>;
    public function helpMessage() : string;
    public function isRequired() : bool;
    public function isOptional() : bool;
    public function isTakesValue() : bool;
    public function defaultValue() : T;
    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, T>;
    public function toImmMap() : ImmMap<string, Option<T>>;
}
