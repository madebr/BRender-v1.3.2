#!/usr/bin/env perl

use strict;
#
# Generate initial data structures and header file for pre-defined tokens
#

my $token_prefix = "BRT_";
my $current = 1;

# Read existing token ids
#

my %token_val;
my %token_id;

open(DB,"<tokens.db");

while (<DB>) {
	# Ignore comments
	#
	next if(/^#/);

	if(/^=(\w\w*)/) {
		$current = $1;
		next;
	}

	# name type id
	#
	if(/\s*(\w\w*)\s*(\w\w*)\s*(\w\w*)/) {
		$token_val{$1} = $2;
		$token_id{$1} = $3;
	}
}

close(DB);

my %type_ext;
my %type_tok;
my %type_member;

# Read all tokens into an array
#
while (<>) {

	# strip out windows newlines
	s/\R\z//;

	# Ignore comments
	#
	next if(/^#/);

        my $name;

	# Look for a type definition
	#
	# if(/^\$\s*(\w\w*)\s*(\w*)/) {
	if(/^\$\s*(\w+)(?:\s+(\w+)\s+(\w+)?)?$/) {
		# Add type to type table
		#

		$name = "\U$1";

		$type_ext{$1} = $2;
		$type_tok{$1} = $name;
		$type_member{$1} = $3;

		# Create token for type
		#
		if(!$token_val{$name}) {
			$token_val{$name} = "none";
			$token_id{$name} = $current++;
		}

		next;
	}

	# Look for a token definition
	#
	if(/\s*(\w\w*)\s*(\w\w*)/) {

		die "Unknown type: $2" unless $type_tok{$2} ;

		my $name = "\U$1$type_ext{$2}";
		my $value = $2;

		if(!$token_val{$name}) {
			$token_val{$name} = $value;
			$token_id{$name} = $current++;
		}
	}
}

#foreach $t (sort(keys %token_val)) {
#	print "$t = $token_val{$t} $token_id{$t} $token_len{$t}\n";
#}

# Header file
#
open(STDOUT,">pretok.h");

	print <<END;
/*
 * Copyright (c) 1993-1995 Argonaut Technologies Limited. All rights reserved.
 *
 * Predefined tokens generated via tokgen.pl
 */
#if BR_TOKEN_ENUM

typedef enum {
END

foreach my $t (sort(keys %token_val)) {
	printf("	%-30s = %8s,\n",
		"$token_prefix$t",
		"$token_id{$t}");
}
	print <<END;
	_BRT_MAX = 0x7ffffff	/* Forces enum to be 32 bit */
} br_token;
#else
END

foreach my $t (sort(keys %token_val)) {
	printf("#define %-30s %8s\n",
		"$token_prefix$t",
		"$token_id{$t}");
}

	print <<END;
#endif
END

# Spit out some macros for glueing a token base name to a type
#
foreach my $t (sort(keys %type_tok)) {
	print("#define BRT_AS_$type_tok{$t}(tok)	BRT_##tok##$type_ext{$t}\n") if ($type_ext{$t});
}
close(STDOUT);

# Assembly include fule
#
open(STDOUT,">pretok.inc");
foreach my $t (sort(keys %token_val)) {
	printf("%-35s EQU %8s\n",
		"$token_prefix$t",
		"$token_id{$t}");
}
close(STDOUT);

# Predefined table
#
open(STDOUT,">pretok.c");

foreach my $t (sort(keys %token_val)) {
	my $len = length($t) - length($type_ext{$token_val{$t}});

	printf("\t{ {0,}, %-32s%-24s%-32s%8d},\n",
		"\"$t\",",
		"$token_prefix$type_tok{$token_val{$t}},",
        "$token_prefix$t,",
		$len);
}

print "#define NEXT_FREE_TOKEN $current\n" ;

close(STDOUT);

# Type table, sorted by suffix length, largest first
#
open(STDOUT,">toktype.c");

foreach my $t (sort({length($type_ext{$b}) <=> length($type_ext{$a})} keys %type_tok)) {
        my $tsize;
	# https://github.com/crocguy0688/CrocDE-BRender adds size of each token type
	if($type_member{$t}) {
		$tsize = "sizeof(((br_value*)0)->$type_member{$t})";
	} else {
		$tsize = "0";
	}
	printf("\t{ %-24s%-24s%8d, %-32s},\n",
	    "\"$type_ext{$t}\",",
	    "$token_prefix$type_tok{$t},",
	    length($type_ext{$t}),
		$tsize
	);
}

close(STDOUT);

# Dump out a new database
#
open(STDOUT,">tokens.new");

foreach my $t (sort(keys %token_val)) {
	printf("%s %s %s\n", $t, $token_val{$t}, $token_id{$t});
}
printf("=%d\n",$current);

close(STDOUT);
