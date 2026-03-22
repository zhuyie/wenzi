# wenzi Architecture Proposal

## 1. Project Goal

`wenzi` is a minimal text editor. The goal is not to accumulate features quickly, but to build a long-term sustainable architecture for text editing, native UI integration, Unicode-aware layout, and future GPU-accelerated rendering.

The project should remain small, understandable, and controllable. Core functionality must stay independent from platform UI details. External dependencies should be kept to a minimum.

## 2. Product Positioning

- Minimal text editor
- Native UI on each platform
- Lightweight dependency strategy
- C/C++ based core
- Unified CMake-based build system
- Architecture designed for future complex text layout and rendering

## 3. Technical Constraints

### 3.1 Languages

- Core language: `C/C++`
- Current C++ upper bound: `C++11`
- C standard: `C11`
- Objective-C++ code must also remain compatible with C++11 constraints

### 3.2 Build System

- Use `CMake` for the whole project
- Keep top-level CMake focused on configuration, options, warnings, and subdirectory composition

### 3.3 Dependency Policy

- Avoid heavyweight foundational libraries such as `ICU`
- Avoid editor frameworks that hide text system control
- Prefer project-owned text handling logic where practical
- Accept narrowly-scoped libraries when they solve a specific rendering problem well

### 3.4 Allowed External Libraries

- `FreeType` for glyph rasterization
- `HarfBuzz` for shaping

These are acceptable because they address specific rendering tasks without taking over the whole text processing stack.

## 4. Architecture Principles

### 4.1 Layering

The project should be structured into three layers:

- `core/`
- `ui/`
- `app/`

This separation is mandatory.

### 4.2 Responsibilities

#### `core/`

Responsible for:

- document model
- text storage
- editing operations
- undo/redo
- file loading and saving
- encoding detection and conversion
- text segmentation support
- internal layout-related data types

Must not depend on platform UI frameworks.

#### `ui/`

Responsible for:

- native windows
- input handling
- IME integration
- clipboard
- scrolling
- rendering host
- layout consumption
- painter implementation

Platform-specific code belongs here.

#### `app/`

Responsible for:

- process startup
- application assembly
- wiring `core` and `ui`
- configuration bootstrap

It should not contain core editing logic.

## 5. Text Model Requirements

### 5.1 Internal Representation

- Internal text representation should be unified
- Recommended choice: `UTF-8`

This keeps storage compact while still allowing full Unicode support, provided the editor does not confuse byte offsets with user-visible text units.

### 5.2 Required Distinctions

The architecture must clearly distinguish:

- byte offset
- code point
- grapheme cluster
- glyph cluster

These are not interchangeable and must not be treated as the same abstraction.

### 5.3 Editing Semantics

Cursor movement, selection, deletion, and layout must not be designed around raw byte stepping. The editor may use byte offsets internally for storage access, but user-facing editing behavior must evolve toward grapheme-aware semantics.

## 6. File Encoding Requirements

### 6.1 Required Capability

The editor must detect text file encodings and automatically convert loaded content into the internal representation.

### 6.2 Minimum Encoding Support

- `UTF-8`
- `UTF-8 BOM`
- `UTF-16 LE`
- `UTF-16 BE`
- `UTF-32 LE`
- `UTF-32 BE`
- `GB2312`

Support for common local single-byte encodings can be added later.

## 7. Unicode and Text Layout Requirements

### 7.1 Required Unicode Scope

The architecture must support future implementation of:

- grapheme breaking
- line breaking
- word breaking
- bidirectional text
- shaping

### 7.2 Layout Pipeline

The intended text pipeline is:

1. load UTF-8 text
2. segment text
3. resolve bidi
4. shape text
5. build line layout
6. paint

The current implementation may simplify this, but the architecture must preserve this decomposition.
