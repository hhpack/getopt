<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\OptionParser;
use hhpack\getopt\OptionSet;
use hhpack\getopt\ValueType;
use hhpack\getopt\NamedMatcher;
use hhpack\getopt\OptionValue;
use hhpack\getopt\StringConsumeHandler;

describe(OptionParser::class, function () {
  describe('parse', function () {
    beforeEach(function () {
      $this->args = [ '-nfoo' ];
      $this->parser = new OptionParser([
        new OptionValue(
          new StringConsumeHandler('name', [ '-n', '--name' ]),
          'foo',
          ValueType::Optional
        )
      ]);
    });
    it('return parsed result', function () {
      $result = $this->parser->parse($this->args);

      expect($result->argumentCount())->toBe(0);
      expect($result->optionCount())->toBe(1);
      expect($result->getOption('name'))->toBe('foo');
    });
  });
});
