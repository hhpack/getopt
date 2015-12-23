<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\ArgumentParser;
use hhpack\getopt\OptionSet;
use hhpack\getopt\FlagOption;
use hhpack\getopt\ValueOption;
use hhpack\getopt\ArgumentType;

describe(ArgumentParser::class, function () {
  describe('parse', function () {
    beforeEach(function () {
      $this->args = [ '-nfoo' ];
      $this->options = new OptionSet([
        new ValueOption('name', 'n', 'name', 'foo', ArgumentType::Optional)
      ]);
      $this->parser = new ArgumentParser($this->options);
    });
    it('return extract arguments', function () {
      $result = $this->parser->parse($this->args);

      expect($result->argumentCount())->toBe(0);
      expect($result->optionCount())->toBe(1);
    });
  });
});
