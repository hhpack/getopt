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

interface OptionCollection extends ConstCollection<Option<mixed>>, HelpDisplayable
{
    public function get(string $name) : Option<mixed>;
    public function contains(...) : bool;
    public function hasNoValue(string $name) : bool;
    public function noValues() : ImmMap<string, Option<mixed>>;
    public function hasOneValue(string $name) : bool;
    public function defaultValues() : ImmVector<Pair<string, mixed>>;
    public function oneValues() : ImmMap<string, Option<mixed>>;
    public function validate(Traversable<string> $args) : void;
}
