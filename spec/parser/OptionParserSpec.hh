<?hh //partial

namespace hhpack\getopt\spec\parser;

use hhpack\getopt\parser\OptionParser;
use hhpack\getopt\spec\ValueType;
use hhpack\getopt\spec\NamedMatcher;
use hhpack\getopt\spec\OptionValue;
use hhpack\getopt\spec\RequiredException;
use hhpack\getopt\handler\StringConsumeHandler;

describe(OptionParser::class, function () {
  describe('parse', function () {
    context('when -- not included', function () {
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
    context('when -- included', function () {
      beforeEach(function () {
        $this->args = [ '-nfoo', '--', 'value' ];
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

        expect($result->argumentCount())->toBe(1);
        expect($result->optionCount())->toBe(1);
        expect($result->getOption('name'))->toBe('foo');
      });
    });
    context('when reqired option is empty', function () {
      beforeEach(function () {
        $this->parser = new OptionParser([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'foo',
            ValueType::Required
          )
        ]);
      });
      it('throw required exception', function () {
        expect(function () {
          $this->parser->parse([ 'foo' ]);
        })->toThrow(RequiredException::class);
      });
    });
  });
});
