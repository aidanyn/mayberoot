# Planned features

This document entails currently planned features and will have a tick next to what I am currently working on.

## Core Functionality 
### Better Permission Detection

    Support regex patterns for error matching

    Add common phrases: EACCES, EPERM, must be root, access denied

    Check both stderr and stdout for error patterns

### Output Handling

    Stream output in real-time (not just buffered)

    Handle arbitrarily large outputs

    Preserve ANSI colors from original command

### Exit Code Analysis

    Map exit codes to common permission errors

    Distinguish "needs root" vs "file not found" vs "syntax error"
## User Experience
### Interactive Features

    Colored highlighting for detected errors

    Timeout for user prompts (e.g., auto-cancel after 30s)

    Progress indicators for long-running commands

### Configuration

    Config file for custom error patterns

    CLI flags to disable prompts/colors

    Environment variable overrides

### Documentation

    Man page with exit code explanations

    Example use-cases in README

    Troubleshooting guide for common issues