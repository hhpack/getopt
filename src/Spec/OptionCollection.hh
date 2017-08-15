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

interface OptionCollection extends ConstCollection<Option>, OptionContainer, HelpDisplayable
{
    public function get(string $name) : Option;
    public function contains(...) : bool;
    public function noValues() : ImmMap<string, Option>;
    public function oneValues() : ImmMap<string, Option>;
}
